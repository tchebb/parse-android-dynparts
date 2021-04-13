Purpose
=======
Most devices running Android 10 and higher use Android's [Dynamic Partitions][1]
feature to allow the different read-only system partitions (e.g. `system`,
`vendor`, and `product`) to share the same pool of storage space. This allows
vendors to resize these partitions freely over a device's lifecycle, as long as
the sum of their sizes doesn't exceed that of the physical partition they all
reside in.

The physical partition image that holds multiple Android dynamic partitions is
conventionally named `super.img`, and it holds similar information as an LVM
physical volume does on Linux. Like LVM, the Android userspace makes use of
[Device Mapper][2] to expose each logical partition on its own block device in
`/dev/mapper`.

In true Google fashion, however, Android dynamic partitions use a totally custom
header format that is not compatible with LVM or other similar software. As
such, the only official tools that exist to parse and mount super.img files are
part of Android and depend heavily on Android's frameworks, volume manager, and
init system.

This tool makes it possible to mount Android `super.img` files with a standard
Linux userspace by using a modified version of Google's parsing code to extract
the partition layout from a `super.img` file and converting that layout to a
"concise device specification" that can be read by the existing `dmsetup` tool
and used to instruct Device Mapper to create the appropriate mappings.

[1]: https://source.android.com/devices/tech/ota/dynamic_partitions
[2]: https://www.kernel.org/doc/html/latest/admin-guide/device-mapper/index.html

Usage
=====
 1. Make your `super.img` available as a loop device:
    ```
    losetup -Pr /dev/loop0 system.img
    ```
 2. Create mappings for the dynamic partitions:
    ```
    dmsetup create --concise "$(parse-dynparts/build/parse-dynparts /dev/loop0p2)"
    ```
 3. Access your partitions as `/dev/mapper/dynpart-NAME`!
