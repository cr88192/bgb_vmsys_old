make clean

zip -r -9 ../bgb.pub2/`date -I`_bgbvm_src.zip $(ls -d *)
zip -r -9 ../bgb.pub2/`date -I`_bgbscm_src.zip $(ls -d bgbscm4/*)
