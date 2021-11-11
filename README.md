## Drawin

This is my first experimentation with evolutionaty computing.

It tryies to evolve agents that draw random images, to the point these agents "learns" to draw (copy) a reference image.

<p align="center">
  <img src="https://github.com/heitoradao/drawin/raw/main/docs/evolution_lapse.gif"/>
</p>

### How it works?

* Generates random noises to an empty image.
* The noise is accepted if it result in an aproximation to an image reference, or discarded otherwise.
* As a consequence of this selection, the noises tend to copy the image reference without knowing it.

### Update (2021-11-10)

I made a big mistake.

In my anxiety to perceive the observed behaviour faster, I optimize the algorithm to the point where the evolutionary part got removed. 🤦

<p align="center">
  <a href="https://xkcd.com/221/"><img src="https://imgs.xkcd.com/comics/random_number.png"/></a>
</p>

The evolutionary algorithm was the most important part of this program.
This program definitively was never about copying a bitmap to one location in memory to another in 3 hours.

It *evolved* to this point so smoothly...
Didn't see it coming.

But whatever. I am working on a new versiosn using ParadiseEO & eoLib for the core part.
