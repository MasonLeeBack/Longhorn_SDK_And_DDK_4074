Quick instructions on installing and setting up the NDIS tester.
(This is not intended as a replacement for instructions by WHQL.)


INSTALLING THE SOFTWARE
"ndsetup c:\ndistest" will install the NDISTest in the c:\ndistest
directory.  (Install it where you want it.)  

Do this on two machines.  One machine is client the other is the server.


SETTING UP THE MACHINES
In the client put three network card(s).  These are refered to 
as the test, message, and support cards

Hook up a kernel debugger to the client machine.  (This is not 
required to run the tests.  But it is required to debug problems.)

On the server install two network card(s).  These are refered to as
the message and support cards.

Usually, a debugger is not needed on the server machine.

Connect the test and two support cards together on a private 
network.  Connect the message cards together.


OPTIONS TO SETTING UP THE MACHINES
1c tests (1 Card) only need a test adapter in the client machine.

2c tests (2 cards) can be run with a only a test and support card 
in the client.

2m tests (2 machine) require the complete setup described except
that a support card in the client is not required.

The message cards must be different than the test and support cards.

The message cards can be on the same network as the test and support
cards.

The message cards communicate using Winsock.  The message cards must
be on the same subnet.

The tests will run on a shared network but it is not the prefered 
setup.


STARTING THE NDISTest ON THE SERVER
From the installation directory run the "ndtest.bat" file.  The 
NDIS tester UI will startup.

Go to the TESTS tab.  Select the "server" radio button.
Select the message card and any support cards you want to use.

Press start.  Another window should appear.  It is ready
to participate in tests as directed by the client.


STARTING THE NDISTest ON THE CLIENT
From the installation directory run the "ndtest.bat" file.  The 
NDIS tester UI will startup.

Go to the TESTS tab.  Select the test and message cards.  At this
point the support adapters on the server should show up in the UI.
Select the adapter you want in the test.

Select the "manual tests", check the desired tests or "Select All".  
Or select the "WHQL Cert" tests.  And press start.

The UI window should appear and tests should start running.


WHERE TO GET HELP

If you encounter a problem, have a question, comment, or suggestion, please
send e-mail to ndiststr@microsoft.com.  This alias will be monitored, and
we will try to respond in a timely fashion to any questions.


