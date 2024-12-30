#include <cstdlib>
#include "../libs/patcher.hpp"

#include <clicky/clicky.hpp>


// Default path for the game executable
std::string PATHSRC = std::string(getenv("HOME")) + "/.local/share/Steam/steamapps/common/Balatro/Balatro.exe";

int main(int argc, char* argv[]) {
  clicky cli;
  Patcher patch;

  cli.add_argument("patch", "m", false, "Path to the folder containing the patch");
  cli.add_argument("source", "s", false, "Path to the source executable");
  cli.add_flag("revert", "r", false, "Reverts the executable to the original Balatro");

  cli.parse(argc, argv);

  try {
    if (!cli.flag("revert")) {
      std::string patchPath = cli.argument("patch");
      patch.updateContents(PATHSRC, patchPath);


      if (!cli.argument("source").empty()) {
        patch.updateContents(cli.argument("source"), patchPath);
      }
    }

    patch.revert(PATHSRC);
  } catch (std::exception& err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

