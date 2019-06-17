python midi_converter.py -i mfig.mid -n MARRIAGE_OF_FIGARO -o ../firmware/drsstc_firmware/MarriageOfFigaro.cpp --wav --channel_lock
python midi_converter.py -i beethoven_ode_to_joy.mid -n ODE_TO_JOY -o ../firmware/drsstc_firmware/OdeToJoy.cpp --wav --tempo_factor 2
python midi_converter.py -i invent1.mid -n BACH_INVENTION -o ../firmware/drsstc_firmware/BachInvention.cpp --wav
python midi_converter.py -i rossini_overture_wtellrecorders.mid -n WILLIAM_TELL -o ../firmware/drsstc_firmware/WilliamTell.cpp --wav