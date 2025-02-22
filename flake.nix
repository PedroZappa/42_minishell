{
  description = "C/C++ environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    utils,
    ...
  } @ inputs:
    utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
        llvm = pkgs.llvmPackages_latest;
        lib = nixpkgs.lib;

        # simple script which replaces the functionality of make
        # it works with <math.h> and includes debugging symbols by default
        # it will be updated as per needs

        # arguments: outfile
        # basic usage example: mk main [flags]
        mymake = pkgs.writeShellScriptBin "mk" ''
          if [ -f "$1.c" ]; then
            i="$1.c"
            c=$CC
          else
            i="$1.cpp"
            c=$CXX
          fi
          o=$1
          shift
          $c -ggdb $i -o $o -lm -Wall $@
        '';
      in {
        # DEV SHELL
        devShell =
          pkgs.mkShell.override {
            stdenv = pkgs.clangStdenv;
          } rec {
            name = "C";

            nativeBuildInputs = [
              pkgs.cmake
              llvm.lldb
              pkgs.clang-tools
              llvm.clang
              pkgs.gtest
            ];

            buildInputs = [
              pkgs.libcxx
            ];
            CPATH = builtins.concatStringsSep ":" [
              (lib.makeSearchPathOutput "dev" "include" [llvm.libcxx])
              (lib.makeSearchPath "resource-root/include" [llvm.clang])
            ];
            # CPATH = "~/.nix-profile/include";
            LIBRARY_PATH = "~/.nix-profile/lib";
            QTDIR = "~/.nix-profile";

            packages = with pkgs; [
              # builder
              gnumake
              cmake
              bear

              # debugger
              llvm.lldb
              gdb

              # fix headers not found
              clang-tools

              # LSP and compiler
              llvm.libstdcxxClang

              # other tools
              cppcheck
              llvm.libllvm
              valgrind
              mymake

              # stdlib for cpp
              llvm.libcxx

              # libs
              glm
              SDL2
              SDL2_gfx
            ];
          };
      }
    );
}

