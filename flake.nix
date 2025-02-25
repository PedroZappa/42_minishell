{
  description = "Minishell development environment with Neovim";
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
              utf8proc
            ]);
          cmakeFlags =
            oa.cmakeFlags
            ++ [
              "-DUSE_BUNDLED=OFF"
            ];
        });
      };
    }
    // flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        overlays = [self.overlay];
        inherit system;
      };
    in rec {
      packages = with pkgs; {
        inherit neovim;
      };
      devShells.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          neovim # Custom Neovim from overlay
          gcc # Compiler for minishell
          readline # For minishell input
          gnumake42 # Makefile support
          clang # Optional: alternative compiler
          clang-tools # Optional: linting/formatting
        ];
        shellHook = ''
          echo "Minishell development environment with Neovim loaded"
        '';
      };
    });
}
