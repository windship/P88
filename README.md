# P88
Easy P88SR launcher 

<a href="https://archive.org/details/88emu-100">'P88SR'</a> is a nice PC-8801 emulator for PC-98 dos system, but it's not so simple to run it.<br>
You have to merge multiple *.D88 disk image files into one file, or need to add whole D88 file names by one-line parameter behind the command.<br>
For example, you have to type like this:

<b>'P88SR.EXE /l /S DISK1.D88 DISK2.D88 DISK3.D88 DISK4.D88 DISK5.D88 DISK6.D88'</b>

Yeah, it's so foolish.<br>
I really didn't want to do such a thing, so I thought and found a solution.<br>
No image mergement needed, and no long filename parameter needed too.

Try and enjoy!
<br><br>


# Usage
  
 1) Make a folder at where you want and just put P88.exe file into it. <b>ex) 'B:\D88DISKN\P88.exe'</b>
 2) Set D88DISKN folder in your path from AUTOEXEC.BAT. <b>ex) 'path=B:\;B:\D88DISKN;'</b>
 3) Reboot your PC-98 once to make your path setting enable.
 4) Go to the directory including D88 files what you want play.
 5) Type 'D88' to execute. It will start to search *.D88 files in your current folder.<br>
    If the searching is done, it will make one-line parameter using all disk filename.<br>
    It using just DOS filename by NAME order. If you want to change the order of disks, just rename them.
 6) You can add P88SR's option parameters behind 'P88.exe'.<br>
    <b>'P88 /l'</b> will execute <b>'P88SR /l 1.D88 2.D88...'</b>.
 7) You can add '#n' option parameter behind 'P88.exe' to set a specific disk on the first disk drive.<br>
    Some games shows different result by booting with 2nd/3rd... disk. You can do such a thing with using '#n'.<br>
    'n' means 'n'th disk from the NAME order of disks.<br>
    <b>'P88 /l #3'</b> will execute <b>'P88SR /l 3.D88 1.D88 2.D88...'</b>.

# Copyright
  I used ChatGPT for entire code of this.<br>
  I didn't programmed at all for this program, I just explained my idea and ordered to code it.<br>
  So I don't want to tell my copyright strongly. Just enjoy, fork and enhance it if you want :)
