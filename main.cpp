#include <liblp/liblp.h>

#include <iostream>

using namespace android::fs_mgr;

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " device" << endl;
    return 1;
  }

  auto metadata = ReadMetadata(argv[1], 0);
  if (!metadata) {
    cerr << "Failed to parse metadata from \"" << argv[1] << "\"" << endl;
    return 1;
  }

  for (auto p : metadata->partitions) {
    cout << p.name << endl;
  }

  return 0;
}
