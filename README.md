# codeBeautifier

## Disclaimer
This readme was written prematurely. The Project is about 75% done, 
not including testing

<!-- what the project does, why to use it, examples, how to use it (installation), command line syntax-->
## :sparkles: What is codeBeautifier?


Code Beautifier takes your C/C++ code, and makes it beautiful.
Ever wanted your code to just look like the lyrics of your favourite song,
or poem? Or upload a an article on why dark theme is better than light theme 
on your light themed colleges repository? Now you can. Just Run this command 
line tool with a C/C++ file and a text file of your choosing and code beatifier
will create a more beautiful (but still functional) version of your code.

## :globe_with_meridians: Setup 

Well, the project is not at a complete stage yet, so the setup
will be edited when it is complete.
 
## Command Line Syntax 

``` 
./codeBeautifier [options] [InputCodeFile] [InputTextFile] 
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
This feature is included because codeBeautifier works better the closer the
word counts of the files are. Count mode will give you an estimate of how close
they are (with uniqueness and keywords taken into account).  

Here is the syntax:
```
./codeBeautifier -count [InputCodeFile] [InputTextFile]
```
No other options will be recognized if the -count flag is used.


## Limitations + Tips For Best Success
Some things are not availible currently (and some things will never be).
Code Beautifier takes use of the define functionality that C offers, unfortunately,
this adds some limitations.

##### Avoid repeating words
Identifiers in c/c++ have to be unique of course. So my algorithm will tie together non-unique words
with what is before or after it to make it unique. Not as beautiful as it could be but still does the job.
Just maybe think twice before throwing the lyrics to yellow submarine in, it may not be underscored to smitherines.

##### Avoid Keywords
I know, words like volatile and enum are so hard to avoid. It is possible to define keywords it's just scary.
Words like for, while, if, else, will all be black listed for sure, and treated like repeating words. Words like
and, or, and not may be (or have the option) to be white listed because I don't know many people who use them over &&
|| and !.

##### No Punctuation!!!
This one isn't my lack of programming finesse, it's not my fault!
Identifiers just can't have punctuation! For now all punctuation is just removed.
Maybe in the future I could make sentence endings and pausers into semi-colons. But for now
just avoid putting punctuation in your text files if you can avoid it.

##### Numbers Won't look Pretty
As we all know, identifiers must not start with numbers. But this isn't a very big deal.
All the numbers 0:9 will be replaced with zero through nine, and everything else will just be
underscored out.

##### Check How Long Your files are in relation to each other
Just make sure they are about the same size and everything will be fine. The algorithm can condense and expand
the code file, but if it has to condense the text file you may not be happy with your results. If the text file has
way more words than the code file, the algorithm will end up tying words in the text file together with underscore to 
even it out. And that's not as pretty :cry:

##### Avoid cpp files that have a lot of preprossessor logic
I very rarely use or see anything besides, include, define, or pragma for headers.
I cannot define anything to be preprossesor functions or their arguments. My solution is to just through all cpp lines
starting with # into a header file and include that one header file. Unfortunately this will not work for something like an
\#ifndif HEADER block, because the \#endif would be thrown right under it. This would hold true for any other wierd preprossessor
functionality I've never seen. So bear it in mind.

 
