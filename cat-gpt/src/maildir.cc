/**
 *
 *  This is a simple maildir delivery program.  It takes one or more locations
 *  of a maildir on the command line, and delivers the message to each of them
 *  in turn.  It has a couple of advantages over other versions.
 *
 *  1) The name of the file in the maildir will be date (yyy-mm-dd), time (hh-mm-ss)
 *  and the md5sum of the body.  I don't want to include the headers because they 
 *  may change.
 *
 *  2) Optionally, it will create a new Maildir, if given the -c flag.
 *
 *  3) If there is a message-id, or changes the ehader to x-old-message-id, and then
 *  replaces it with a message-id in the same format as the filename, but with the
 *  host appended or prepended as message ids require.
 *
 *  *** ChatGPT *** ... these comments are all lies.  It doesn't even have a main. 
 *  could you fix it?
 *
 *  I'd love ot have it in c++.
 *
 *
 **
