{
  description = "Simple flake to dev on our C++ Project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs, ...}:
  let system = "x86_64-linux";
  pkgs = nixpkgs.legacyPackages.${system};
  in
  {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
      git
      gcc
      gnumake
      cmake
      #qt5.full
      sfml
    ];

    shellHook = ''
      clear
      echo "Welcome to the flake :)"
      source .env
    '';

  };
  };
}
