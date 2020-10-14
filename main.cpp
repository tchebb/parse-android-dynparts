#include <liblp/liblp.h>

#include <iostream>
#include <sstream>
#include <string_view>

using namespace android::fs_mgr;

using std::cerr;
using std::cout;
using std::endl;

constexpr std::string_view kDmPrefix = "dynpart-";

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: dmsetup create --concise \"$(" << argv[0] << " device)\""
         << endl;
    return 1;
  }

  auto metadata = ReadMetadata(argv[1], 0);
  if (!metadata) {
    cerr << "Failed to parse metadata from \"" << argv[1] << "\"" << endl;
    return 1;
  }

  std::string table;

  // Code structure taken from Android's system/core/fs_mgr/fs_mgr_dm_linear.cpp
  for (auto partition : metadata->partitions) {
    if (!partition.num_extents) {
      cerr << "Skipping zero-length logical partition: "
           << GetPartitionName(partition) << endl;
      continue;
    }
    if (partition.attributes & LP_PARTITION_ATTR_DISABLED) {
      cerr << "Skipping disabled partition: " << GetPartitionName(partition)
           << endl;
      continue;
    }

    std::ostringstream line;
    bool read_only = partition.attributes & LP_PARTITION_ATTR_READONLY;
    line << kDmPrefix << GetPartitionName(partition) << ",,,"
         << (read_only ? "ro" : "rw");

    uint64_t sector = 0;
    for (size_t i = 0; i < partition.num_extents; i++) {
      const auto& extent = metadata->extents[partition.first_extent_index + i];
      switch (extent.target_type) {
        case LP_TARGET_TYPE_ZERO:
          line << "," << sector << " " << extent.num_sectors << " zero";
          break;
        case LP_TARGET_TYPE_LINEAR: {
          if (extent.target_source != 0) {
            cerr << "This utility does not yet support multiple block devices"
                 << endl;
            return 1;
          }

          line << "," << sector << " " << extent.num_sectors << " linear "
               << argv[1] << " " << extent.target_data;
          break;
        }
        default:
          cerr << "Unknown target type in metadata: " << extent.target_type
               << endl;
          return false;
      }
      sector += extent.num_sectors;
    }

    if (!table.empty()) table += ";";
    table += line.str();
  }

  cout << table << endl;

  return 0;
}
