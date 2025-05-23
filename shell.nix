with import <nixpkgs> {};

mkShell {
  buildInputs = [
    cmake
    sfml
    # Add other dependencies here
  ];

  shellHook = ''
    export SFML_DIR="${sfml}/lib/cmake/SFML"
    echo "SFML configured at: $SFML_DIR"
  '';
}