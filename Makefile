GBDK_CC=bin/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j
PNGGB=python3 pnggb.py
TMXGB=python3 tmxgb.py
MGBA_BIN=bin/mgba/mgba

test: a.gb
	$(MGBA_BIN) a.gb 2> logs/mGBA-log-$(shell date +%s).txt
	# run the clean after the test
	$(MAKE) clean

a.gb: asset-compile *.c 
	$(GBDK_CC) *.c

.PHONY: test clean make-assembly asset-compile edit-map

make-assembly: asset-compile *.c 
	$(GBDK_CC) -S -o a.s *.c

asset-compile:
	$(PNGGB) cube.png > cube.h
	$(PNGGB) bkg.png > bkg.h
	$(TMXGB) area1.tmx > area1.h

clean:
	rm *.map *.noi *.sav