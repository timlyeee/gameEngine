# README

Renderpipeline should be the individual module which accept an easy way to implement.

As each time draw element requires a command, we should first collect all things to draw, and then draw it together if they can be shown. It might be the principal of deferred pipeline.

Final cut of the game should be the composition of the cameras specified.

In one scene there might be several cameras.

I'm not quiet understand if I should consider to make the scene as a part of the renderpipeline, but it's better to just get the input.

Frame sync between CPU and GPU is vital. I will put it to TODO list, right now it has just a feature, or bug I guess.