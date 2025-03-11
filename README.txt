Balatro Patcher(y)

patchy, a tool I wrote to facilitate modding Balatro in linux 
(since you can just do what this does in windows).

It's not perfect, just like every repo of mine, but it does the job.
The usage and compilation are easy enough, I will include prebuilt binaries
on the releases page, but since this isn't a BIG project, unless the entire
Balatro folder structure changes, I won't be updating this too much.

If you want to compile it by yourself, you'll need my library clicky (https://github.com/auth-xyz/clicky)
After making sure clicky is installed, all you have to run is `make`.
That's it!

For how to use patchy, it's pretty simple, straight forward.
By default, patchy will look for "Balatro.exe" inside the ~/.local/share/Steam/steamapps/common/Balatro/ folder
IF your Balatro installation is not there (for whatever reason, if you pirated it I will be very angry), you can
give patchy the --source flag, and it will use that path instead.

./patchy --patch /path/to/patch_folder

This will patch the "Balatro.exe" to have the contents of the mod folder.
Now of course, if you want to play your game with no modded content, you can use:

./patchy --revert

And your Balatro.exe will be clean!

If you have any questions, comments, or concerns, please open an issue on the repo.
(or suggestions)

Have fun modding!
