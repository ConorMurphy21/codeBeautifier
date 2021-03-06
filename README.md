# Code Beautifier

## Disclaimers:exclamation: 
1. This project is not yet stable.  

2. This software has possible malicious use. I do not condone the malicious
use of this software. Please use responsibly!

<!-- what the project does, why to use it, examples, how to use it (installation), command line syntax-->
## :sparkles: What is Code Beautifier?

Code Beautifier takes your C/C++ code, and makes it beautiful.
Ever wanted your code to just look like the lyrics of your favourite song,
or poem? Or upload an article on why dark theme is better than light theme 
on your light themed colleges repository? Now you can. Just Run this command 
line tool with a C/C++ file and a text file of your choosing and Code Beautifier
will create a more beautiful (but still functional) version of your code.  
here are some [examples](https://github.com/ConorMurphy21/codeBeautifier/tree/master/examples)

## Setup :globe_with_meridians: 

I have included a windows installer in the source directory,
make sure to allow codeBeautifier to add itself to the path variable,
from there follow the command line syntax

Currently working on making the installer cross platform
This will soon be updated! :alarm_clock:
 
## :page_with_curl:Command Line Syntax

``` 
./bfy [options] [InputCodeFile] [InputTextFile] 
```

Where:
 * [options] are any of the flags listed below
 * [InputCodeFile] is the C/C++ file you would like to convert
 * [InputTextFile] is the text you would like to convert [InputCodeFile] to
 
 by default:
 * the new file will be written to beautiful_[InputCodeFile]
 * the new file will link a header file called Definitions.h 
 with all the definitions
 
#### Options

* ```-f``` leave the definitions in the output InputCodeFile, 
instead of linking a definitions header
* ```-o``` sets the output code file to [InputCodeFile], and will overwrite
anything in the output header file and source file
* ```-s [outputCodeFile]``` set the output code file to be [outputCodeFile]
* ```-h [outputHeaderFile]``` set the output header/definitions file to be [outputCodeFile]
* ```-d [outputFileName]``` Note: [outputFileName] must not have a file extension
sets the output source file to [outpuFileName] with the same file extnesion as [InputCodeFile]
and the output header file to [outputFielName].h

#### Count Flag

The count flag is a special flag that just counts the number of words in each file.
This feature is included because Code Beautifier works better the closer the
word counts of the files are. Count mode will give you an estimate of how close
the word counts (with uniqueness and keywords taken into account).  

Here is the syntax:
```
./codeBeautifier -count [InputCodeFile] [InputTextFile]
```
No other options will be recognized if the -count flag is used.


## Limitations :boom: + Tips For Best Success :star2:
Some things are not available currently (and some things will never be).
Code Beautifier makes use of the define functionality that C offers, unfortunately,
this adds some limitations.

##### Avoid repeating words
Identifiers in c/c++ have to be unique of course. So my algorithm will 
tie together non-unique words with what is before or after it to make 
it unique. This is not as beautiful as it could be but it still does the job.
Just maybe think twice before throwing the lyrics to all star in, 
it may be underscored to smithereens. Or just do it anyway, It's still fun!

##### No Punctuation!!!
This one isn't due to my lack of programming finesse. It's not my fault!  
Identifiers just can't have punctuation! For now all punctuation is just removed.
Maybe in the future I could make sentence endings and pausers into semi-colons. 
The algorithm can handle clearing out punctuation, but don't expect your
ascii art to work.

##### Numbers might not look pretty :woman_shrugging: 
As we all know, identifiers must not start with numbers. No Biggie.
All the numbers 0:9 will be replaced with zero through nine, and everything 
else will just be underscored out ie 99 will be _99.

##### Check How long your files are in relation to each other
Just make sure they are about the same size and everything will be fine. 
The algorithm can condense and expand the code file, but if it has to 
condense the text file you may not be happy with your results. If the 
text file has a lot more words than the code file, the algorithm will 
end up tying words in the text file together with underscore to 
even it out. And that's not as pretty :cry:.

##### Avoid source files that have a lot of preprocessor logic
I very rarely use or see anything besides, include, define, or pragma for headers.
I cannot define anything to be preprocessor functions or their arguments. My solution is to throw
all the preprocessor below all the definitions in the included Definitions file. 
If this is just a couple includes then everything will be fine and dandy, anything else
may cause errors.

 
