# assault-cube-hack

After reversing the game Assault Cube, this is a memory hack using Windows API to change certain bytes of the game.

## Method

It uses Arrays of Bytes to find where certain elements are stored in the game (like health and ammo). It used Windows API to find these processes and read these bytes. I have custom functions written to help scan for these elements

Then it uses Windows API functions like "VirtualProtect" to overwrite the values. All of this functionality is wrapped in a terminal that is listening for specific user inputs (for instance, pressing F1 will give the player unlimited ammo. 

## Development Time

This project was worked on in a week sprint following many tutorials for reversing and byte modifying. 
