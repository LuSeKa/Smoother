# Smoother

This project was inspired by James Bruton's video on servo smoothing.
He uses a discrete low pass filter on the input signals to servo motors 
to achieve the desired smoothing effect.
This library here provides the same functionality in a more concise and 
reusable way.

On top of that, it can easily be used as a low pass filter wherever one 
is needed.
While we're at it, I thought it would be fun to demonstrate what a low 
pass filter does.
The following examples are generated with the low_pass_filter example 
contained in this library.

## Low pass filter demo

As the name implies, a low pass filter lets low frequency components of 
a signal pass, but not high frequency ones. 

Why would we want that?
In signal transmission, there is often a useful part of the signal with 
relatively low frequency components and disturbancs or signal noise with
comparatively high frequencies. To retrieve the useful signal we want to 
filter out the high frequency components and only let the low frequency 
ones pass - that's exactly what a low pass filter does! 
A practical example is differentiation noise that we get when trying to
compute wheel speed from a wheel position encocer via discrete
differentiation. 
To get a more useful speed signal, we need to filter out that noise.

In the case of this first order low pass filter the distinction between 
low and high frequencies is not as clear cut though.
More generally speaking, this low pass filter attenuates high 
frequencies much more than low ones. 
But let's look at this with some examples!
