{
  description = "SimpleGame with SFML 2.5.1";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/22.11";  # Corrected branch reference
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux"; # or "aarch64-darwin" for Apple Silicon
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          cmake
          sfml
          libGL
          libGLU
          xorg.libX11
        ];

        shellHook = ''
          echo "SFML ${pkgs.sfml.version} environment ready!"
          echo "Include path: ${pkgs.sfml}/include"
          export SFML_DIR="${pkgs.sfml}/lib/cmake/SFML"
        '';
      };
    };
}