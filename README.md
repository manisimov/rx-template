# rx-template

I use this project as a template for YRDKRX62N dev. board with Renesas RX600 microcontroller.

Docker image from [here](https://github.com/manisimov/rx-gcc-docker) has everything needed for building and debugging.

When the image is ready, start a new container with:

        ./dock.sh start
        
Build the project (inside container):

        mkdir build
        cd build
        cmake ../
        make
        
Start GDB server:
        
        make gdbser
        
In a new terminal window open a new shell session with the container:

        ./dock.sh attach
        
In this new window run cgdb (with downloading image to the flash):

        cd build
        make cgdbl

or without flashing:

        cd build
        make cgdbr
