<html>
<head>

</head>
<body>
<h1>Digital Audio Workstation</h1>
<p>An open-source, cross platform implementation of a
Digital Audio Workstation, written in C++. Making use 
the QT application framework.</p>

<h2>Audio Process Flow</h2>
<p>Audio buffer size is set to n samples at a global level.
Each track owns a double buffer at size n. 
</p>
<p>The mixer owns a thread pool that process events as tasks.
</p>
<p>For every global write buffer, in the main thread we 
loop through all tracks, and push the task of adding the track
data to a master buffer. </p>
<p>Once all tracks have been mixed to the buffer, a mutex and conditional 
is used to complete functionality where the master buffer is mixed (back in the main thread).
</p>
<p>The data is then pushed to the global ring buffer.</p>
<p>The high priority audiocallback thread then pops data from the ring buffer
to the applied output device.</p>
<h2>Midi Process Flow</h2>
<p>playback midi is parsed from two seperate places. with midi clips owning their own 
clip manager, allowing them to pass events to instruments to generate audio, this is processed in 
the mixer thread pool, for every block.</p>
<p>In addition to that, midi is sent via midi messages from a project level midi dispatcher. </p>
<p>This allows live midi recording, by pushing to the same track midi ring buffer that the midi clip manager pushes to.</p>
<h2>Required Libraries</h2>

<h3>Rt audio</h3>
<p>Implements a live two way stream between
input and output devices. Settings up a high priority
thread that has a singular audio callback that reads 
from a projects double ring buffer.</p>

<h3>Sndfile</h3>
<p>Enables deserialising audio assets of a variety of 
filetypes from memory locations and storing their data
on the heap. This is processed instantly 
for small files and on a worker thread in chunks for large files
<i>n</i> chunks infront of the playhead curser</p>

<p>Also enables serializing of recorded, or bounced audio data
to .WAV assets for storage in a local file system.</p>

<h3>Craig Sapp - midifile</h3>
<p>Enables bidirectional parsing of midi files in a .MIDI
format. Used to convert raw midi byte data into supported 
data structures that can be used in the program.</p>

</body>
</html>
