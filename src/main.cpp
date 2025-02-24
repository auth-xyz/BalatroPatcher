#include "../libs/patcher.hpp"
#include <cstdlib>

#include <clicky/clicky.hpp>

// Default path for the game executable
std::string PATHSRC =
    std::string(getenv("HOME")) +
    "/.local/share/Steam/steamapps/common/Balatro/Balatro.exe";

int main(int argc, char *argv[]) {
  clicky cli("{program} (-m)[Path to modded files]");
  Patcher patch;

  cli.add_argument("patch", "m", "Path to modded content", true);
  cli.add_argument("source", "s", "Path to the source executable", false);
  cli.add_option("revert", "r",
                 "Reverts the executable to the original Balatro", false);
  cli.parse(argc, argv);

  try {
    if (!cli.has_option("revert")) {
      std::string patchPath = cli.has_argument("patch")
                                  ? cli.get_argument("patch")
                                  : std::string("patch");

      if (cli.has_argument("source")) {
        patch.updateContents(cli.get_argument("source"), patchPath);
      } else {
        patch.updateContents(PATHSRC, patchPath);
      }
    } else {
      patch.revert(PATHSRC);
    }

  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
