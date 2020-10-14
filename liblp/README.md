liblp
=====

This code is based on `fs_mgr/liblp` from Android's `platform/system/core`
project. However, I've removed most of the files and edited the ones that remain
so that they build independently from the rest of the AOSP codebase. All
functions still declared in the local copy of `include/liblp/liblp.h` ought to
work. `CMakeLists.txt` is not from upstream and was authored by me to replace
upstream's `Android.bp`.

Currently derived from the upstream tree at [commit f9c36a2ca632][1].

[1]: https://android.googlesource.com/platform/system/core/+/f9c36a2ca632fa88edba9c2c87f14f2aec1e7fd3/fs_mgr/liblp/
