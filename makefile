#----------------------------------------------------------------------------
# Author: 
# Date: 
#----------------------------------------------------------------------------

#
# First declare aliases for use later on
#
CC              = g++
CFLAGS          = -g -Wall -pedantic -Icurl/include/ -Lcurl/lib -lcurl -lpthread
CPPFLAGS        = $(CFLAGS)
LIBS            = # -lm  for use if you need math or other libs

#EXE_LOCATION    = /home/ryan/CS/CS3505/executable/project3/
#EXE_LOCATION    = /home/class/CS/CS3505/executable/project3/
#EXE_LOCATION 	 = /home/Braden/
#EXE_LOCATION	= /Users/aldobaie/Desktop/CS3505/cs3505_shared/project3/
EXE_LOCATION    = /home/aldobaie/cs3505/cs3505_shared/project3/
#EXE_LOCATION    = /Users/nathanpatterson/spring2012/cs3505/project3/src/

FOLDER_OFFSET   = 
#FOLDER_OFFSET   = 
EXE_NAME        = crawl

################################################################
# ALL
#
# when you run make by itself, this is what it will try to create
#
all: $(EXE_LOCATION)$(EXE_NAME)


################################################################
#
# Dependencies
#

$(EXE_LOCATION)$(EXE_NAME): \
	$(EXE_LOCATION)commandParser.o \
	$(EXE_LOCATION)project3CommandParser.o \
	$(EXE_LOCATION)textFileReader.o \
	$(EXE_LOCATION)word.o \
	$(EXE_LOCATION)url.o \
	$(EXE_LOCATION)robots_txt.o \
	$(EXE_LOCATION)dictionary.o \
	$(EXE_LOCATION)product.o \
	$(EXE_LOCATION)webCrawler.o \
	$(EXE_LOCATION)comment.o \
	$(EXE_LOCATION)global_web_data.o \
	$(EXE_LOCATION)Customer.o \
	$(EXE_LOCATION)misspelled_word.o \
	$(EXE_LOCATION)output.o \
	$(EXE_LOCATION)recovery.o \
	$(EXE_LOCATION)webpage.o \
	$(EXE_LOCATION)word_count.o \
	main.C \
	$(FOLDER_OFFSET)bst.h \
	$(FOLDER_OFFSET)bstNode.h \
	$(FOLDER_OFFSET)commandParser.h \
	$(FOLDER_OFFSET)project3CommandParser.h \
	$(FOLDER_OFFSET)textFileReader.h \
	$(FOLDER_OFFSET)word.h \
	$(FOLDER_OFFSET)url.h \
	$(FOLDER_OFFSET)robots_txt.h \
	$(FOLDER_OFFSET)dictionary.h \
	$(FOLDER_OFFSET)product.h \
	$(FOLDER_OFFSET)webCrawler.h \
	$(FOLDER_OFFSET)comment.h \
	$(FOLDER_OFFSET)global_web_data.h \
	$(FOLDER_OFFSET)Customer.h \
	$(FOLDER_OFFSET)misspelled_word.h \
	$(FOLDER_OFFSET)hashTable.h \
	$(FOLDER_OFFSET)output.h \
	$(FOLDER_OFFSET)recovery.h \
	$(FOLDER_OFFSET)webpage.h \
	$(FOLDER_OFFSET)word_count.h
	$(CC)  $(CFLAGS) -o $@ \
		main.C \
		$(FOLDER_OFFSET)commandParser.C \
		$(FOLDER_OFFSET)project3CommandParser.C \
		$(FOLDER_OFFSET)textFileReader.C \
		$(FOLDER_OFFSET)word.C \
		$(FOLDER_OFFSET)url.C \
		$(FOLDER_OFFSET)robots_txt.C \
		$(FOLDER_OFFSET)dictionary.C \
		$(FOLDER_OFFSET)product.C \
		$(FOLDER_OFFSET)webCrawler.C \
		$(FOLDER_OFFSET)comment.C \
		$(FOLDER_OFFSET)global_web_data.C \
		$(FOLDER_OFFSET)Customer.C \
		$(FOLDER_OFFSET)misspelled_word.C \
		$(FOLDER_OFFSET)output.C \
		$(FOLDER_OFFSET)recovery.C \
		$(FOLDER_OFFSET)webpage.C \
		$(FOLDER_OFFSET)word_count.C
		

$(EXE_LOCATION)commandParser.o : $(FOLDER_OFFSET)commandParser.C $(FOLDER_OFFSET)commandParser.h
$(EXE_LOCATION)project3CommandParser.o : $(FOLDER_OFFSET)project3CommandParser.C $(FOLDER_OFFSET)project3CommandParser.h
$(EXE_LOCATION)comment.o : $(FOLDER_OFFSET)comment.C $(FOLDER_OFFSET)comment.h
$(EXE_LOCATION)Customer.o : $(FOLDER_OFFSET)Customer.C $(FOLDER_OFFSET)Customer.h
$(EXE_LOCATION)webCrawler.o : $(FOLDER_OFFSET)webCrawler.C $(FOLDER_OFFSET)webCrawler.h
$(EXE_LOCATION)dictionary.o : $(FOLDER_OFFSET)dictionary.C $(FOLDER_OFFSET)dictionary.h
$(EXE_LOCATION)global_web_data.o : $(FOLDER_OFFSET)global_web_data.C $(FOLDER_OFFSET)global_web_data.h
$(EXE_LOCATION)misspelled_word.o : $(FOLDER_OFFSET)misspelled_word.C $(FOLDER_OFFSET)misspelled_word.h
$(EXE_LOCATION)output.o : $(FOLDER_OFFSET)output.C $(FOLDER_OFFSET)output.h
$(EXE_LOCATION)product.o : $(FOLDER_OFFSET)product.C $(FOLDER_OFFSET)product.h
$(EXE_LOCATION)recovery.o : $(FOLDER_OFFSET)recovery.C $(FOLDER_OFFSET)recovery.h
$(EXE_LOCATION)robots_txt.o : $(FOLDER_OFFSET)robots_txt.C $(FOLDER_OFFSET)robots_txt.h
$(EXE_LOCATION)textFileReader.o : $(FOLDER_OFFSET)textFileReader.C $(FOLDER_OFFSET)textFileReader.h
$(EXE_LOCATION)url.o : $(FOLDER_OFFSET)url.C $(FOLDER_OFFSET)url.h
$(EXE_LOCATION)webpage.o : $(FOLDER_OFFSET)webpage.C $(FOLDER_OFFSET)webpage.h
$(EXE_LOCATION)word.o : $(FOLDER_OFFSET)word.C $(FOLDER_OFFSET)word.h
$(EXE_LOCATION)word_count.o : $(FOLDER_OFFSET)word_count.C $(FOLDER_OFFSET)word_count.h

clean:
	rm -f *.o $(EXE_NAME) # make sure there is a tab before rm
