# External packages used by WowStack

The following Open Source projects provide libraries being reused and/or being
customized in the WowStack project.

So, let us express our gratitude for the work you have done. Some libraries in
here have been customized for easier integration, or stripped down into smaller
versions as we did not require full functionality.

## Dependencies

For the sake of eventually having to upgrade/migrate to newer version, we also
use this file to keep track of versions and/or specific commit hashes we use
for external dependencies.

### Recast & Detour

[Recast & Detour][recast] provide us with the basics for constructing meshes
and paths.

License: MIT License
Version used: [commit 54bb094](https://github.com/recastnavigation/recastnavigation/commit/54bb0943e5174a71eeeca11919920f685760a4f0)

### libmpq

[libmpq][mpq] provides access to the game clients MPQ archives.

License: GPL License, version 2
Version used: [commit 707e6f7](https://github.com/ge0rg/libmpq/commit/707e6f7c6d70524e2ff895d9907b93df5e9768d0)

### StormLib

[StormLib][stormlib] implements most (if not all) MPQ archive formats and is
still under active development.

License: MIT License
Version used: [commit efa7e50](https://github.com/ladislav-zezula/StormLib/commit/efa7e50ef7d25bcbb15007deed9453b3002aa8aa)

### G3D engine

[g3d][g3d] provides common 3D objects for handling maps and meshes.

License: Modified BSD License
Version used: [9.0.0](https://sourceforge.net/projects/g3d/files/g3d-cpp/9.00/)

### utf8cpp

[utf8cpp][utf8cpp] is an open-source project providing support for handling
Unicode strings in C++.

License: Boost Software License, version 1.0
Version used: [2.3.4](https://sourceforge.net/projects/utfcpp/files/utf8cpp_2x/Release%202.3.4/)

### Google C++ Testing Framework

The [Google C++ Testing Framework][gtest] provides the foundation for verifying
our work. For every bit of code we submit, we also submit a matching test to
verify it behaves as expected.

License: BSD 3-clause License
Version used: [1.8.1](https://github.com/google/googletest/releases/tag/release-1.8.1)

[recast]: https://github.com/recastnavigation/recastnavigation
[mpq]: https://github.com/ge0rg/libmpq
[g3d]: https://sourceforge.net/projects/g3d/
[spdlog]: https://github.com/gabime/spdlog
[utf8cpp]: http://utfcpp.sourceforge.net/
[gtest]: https://github.com/google/googletest
[stormlib]: https://github.com/ladislav-zezula/StormLib
