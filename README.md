### Compiling
This code was written and tested on a modern Mac running OS 10.11 using gcc.

Run `make` in the code directory to create `as6`.
Run `make test` to compile test runner to create tester program for testing funcitons. 

##### Settings reported by `gcc --version`
```
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/usr/include/c++/4.2.1
Apple LLVM version 7.0.0 (clang-700.1.76)
Target: x86_64-apple-darwin15.0.0
Thread model: posix
```
### Third Party code

[Lib NACL](http://nacl.cr.yp.to/) A library to provide cryptographic primitives. Used for hashing password securely in this program.
[Base 64 codec](https://opensource.apple.com/source/QuickTimeStreamingServer/QuickTimeStreamingServer-452/CommonUtilitiesLib/base64.c) Code snippet from Apple Open source to perform base 64 encoding and decoding.  Base 64 encoding allows binary strings to be stored in files intended for non-binary data, like txt files.
