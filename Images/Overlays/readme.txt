#The overlay folder contains special patterns that are overlaid on background
#patterns and have their own motion settings.  Only the first line is read from
#an overlay file.
#
#To apply motion settings to overlay patterns the following settings are used:
#link_2a =*decimal* 	rotation speed on A axis (like a steering wheel)
#link_2b =*decimal* rotation speed on B axis (like a globe)
#link_2c=*decimal*	(constant rotation)
#
#For transparency overlays the following settings are used:
#these are prefixed "trans_" in the Overlay folder
#
#blend_mode 0 = auto, 1 = screen, 2 = normal (A over B), 3 = normal reversed (B over A)
#
#blend_mode=3
#transparency_color=ffffff (white colors will show the transparency colour)
#overlay=trans_sunset.bmp