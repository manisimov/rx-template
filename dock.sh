#! /bin/bash

command=$1

if [ "$command" == "start" ]; then
    sudo docker run              \
         --name rx_cnt           \
         --net=host              \
         -it                     \
         --rm                    \
         --privileged            \
         -v ${PWD}:/home/project \
         -w /home/project        \
         rx_img                  \
         bash
elif [ $command == "attach" ]; then
    sudo docker exec      \
         -it              \
         -w /home/project \
         rx_cnt           \
         bash
else
    echo Bad arguments. Try \"attach\" or \"start\"
fi
