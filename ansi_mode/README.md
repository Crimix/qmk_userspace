# Ansi Mode
This is a toggle mode that can be used to send keycodes that creates the letters seen on a DK ISO layout to a PC using ANSI (ENG) layout.

The usecase for this is that sometimes I need to use a machine either a VM or something else where pressing the key on my keyboard will create the wrong symbol.
Thus if this mode is toggled on then it will make sure to create *most* of the correct symbols on the target machine.

## Indicator light
If the following is defined `ANSI_MODE_INDEX`, then a key at that index will be lit using the hook `set_custom_indicator`.