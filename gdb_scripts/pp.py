sys.path.append("gdb_scripts")
import sys
import os
import myimp


class HelloWorld (gdb.Command):
  """Greet the whole world."""

  def __init__ (self):
    super (HelloWorld, self).__init__ ("hello-world", gdb.COMMAND_USER)

  def invoke (self, arg, from_tty):
    print ("Hello, World!")
    print (sys.path)
    print (os.getcwd())
    print (myimp.mymy())

HelloWorld ()
