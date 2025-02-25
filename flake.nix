{
  description = "Neovim flake";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    neovim-src.url = "github:neovim/neovim?ref=master";
    neovim-src.flake = false;
  };
  outputs = {
    self,
    nixpkgs,
    flake-utils,
    neovim-src,
  }:
    {
      overlay = final: prev: let
        pkgs = nixpkgs.legacyPackages.${prev.system};
      in rec {
        neovim = pkgs.neovim-unwrapped.overrideAttrs (oa: {
          version = "master";
          src = neovim-src;
          buildInputs =
            oa.buildInputs
            ++ (with pkgs; [
              tree-sitter
              utf8proc # Changed from libutf8proc to utf8proc
            ]);
          cmakeFlags =
            oa.cmakeFlags
            ++ [
              "-DUSE_BUNDLED=OFF"
            ];
        });
        # neovim-debug = let
        #   stdenv = pkgs.stdenvAdapters.keepDebugInfo (
        #     if pkgs.stdenv.isLinux
        #     then pkgs.llvmPackages_latest.stdenv
        #     else pkgs.stdenv
        #   );
        # in
        #   pkgs.enableDebugging (neovim.overrideAttrs (oa: {
        #     lua = pkgs.enableDebugging pkgs.luajit;
        #     inherit stdenv;
        #     cmakeBuildType = "Debug";
        #     cmakeFlags =
        #       oa.cmakeFlags
        #       ++ [
        #         "-DMIN_LOG_LEVEL=0"
        #       ];
        #     disallowedReferences = [];
        #   }));
        # neovim-developer = let
        #   lib = nixpkgs.lib;
        #   pythonEnv = pkgs.python3.withPackages (ps: [
        #     ps.msgpack
        #     ps.flake8
        #   ]);
        #   luacheck = pkgs.luaPackages.luacheck;
        # in
        #   neovim-debug.overrideAttrs (oa: {
        #     doCheck = pkgs.stdenv.isLinux;
        #     cmakeFlags =
        #       oa.cmakeFlags
        #       ++ [
        #         "-DLUACHECK_PRG=${luacheck}/bin/luacheck"
        #         "-DMIN_LOG_LEVEL=0"
        #         "-DENABLE_LTO=OFF"
        #         "-DUSE_BUNDLED=OFF"
        #       ]
        #       ++ pkgs.lib.optionals pkgs.stdenv.isLinux [
        #         "-DCLANG_ASAN_UBSAN=ON"
        #       ];
        #     nativeBuildInputs =
        #       oa.nativeBuildInputs
        #       ++ (with pkgs; [
        #         pythonEnv
        #         include-what-you-use
        #         jq
        #         shellcheck
        #         doxygen
        #         clang-tools
        #       ]);
        #     shellHook =
        #       oa.shellHook
        #       + ''
        #         export NVIM_PYTHON_LOG_LEVEL=DEBUG
        #         export NVIM_LOG_FILE=/tmp/nvim.log
        #         export ASAN_OPTIONS="log_path=./test.log:abort_on_error=1"
        #         export UBSAN_OPTIONS=print_stacktrace=1
        #       '';
        #   });
      };
    }
    // flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          overlays = [self.overlay];
          inherit system;
        };
      in rec {
        packages = with pkgs; {
          inherit neovim neovim-debug neovim-developer;
        };
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            # neovim-developer
            cmake
            gcc
            tree-sitter
            python3
            lua
          ];
          shellHook = ''
            export NVIM_PYTHON_LOG_LEVEL=DEBUG
            export NVIM_LOG_FILE=/tmp/nvim.log
            export ASAN_OPTIONS="log_path=./test.log:abort_on_error=1"
            export UBSAN_OPTIONS=print_stacktrace=1
          '';
        };
      }
    );
}
