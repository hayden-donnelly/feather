{
    description = "Lightweight 2D game framework with an entity-component-system architecture";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/23.11";
        flake-utils.url = "github:numtide/flake-utils";
    };
    outputs = inputs@{ self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-linux" ] (system: let
        inherit (nixpkgs) lib;
        pkgs = import nixpkgs { inherit system; };
    in {
        devShells = rec {
            default = pkgs.mkShell {
                name = "sdl";
                buildInputs = with pkgs; [
                    SDL2
                    SDL2_image
                    gnumake
                ];
            };
        };
    });
}
