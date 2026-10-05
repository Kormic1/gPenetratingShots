# gPenetratingShots

gPenetratingShots is a Union plugin for Gothic 1, Gothic Sequel, Gothic 2 and Gothic NotR. The goal of this plugin is to make bows and crossbows even more enjoyable to use.
It implements arrow shots that have a chance of penetrating enemies, potentially damaging more than one, given they stand in a single file.

The chance of a penetrating shot happening is based on hero's dexterity and the projectile protection of an enemy. The higher the dexterity and the lower the projectile protection, the greater the likelihood of landing penetrating hits.

Here you can watch a demonstration of the plugin (click the image below):

[![Demonstration](http://img.youtube.com/vi/uzivTaVHrYE/0.jpg)](http://www.youtube.com/watch?v=uzivTaVHrYE "gPenetratingShots")

## Probability formula

Before I move on to the probability formula, I will shortly describe two conditions that have to be met before penetrating shot can occur:
1. Your dexterity has to be greater than or equal to `MinDexterity`.
2. Enemy's projectile protection cannot be greater than `MaxProjectileProtection`.

Both of these can be set in **Gothic.ini** file. To change them, paste in the following text there at the end of this file:
```
[GPENETRATINGSHOTS]
MinDexterity=10
MaxProjectileProtection=9999
```
Alternatively, just boot Gothic and let it generate this section automatically there. Feel free to change exemplary values to whatever you like.

Moving on to the formula - there were a few good candidates for probability functions I could use, but I decided to go with a two-variable logistic function. After a bit of tweaking, this is what I came up with:

```math
probability = \frac{1}{1 + exp(-0.012 * (-0.5 * ((dexterity - 300) - 2 * protection)))}
```

Since formulae aren't good for visualisation purposes, here's an image of the probability function shown above:

![3D plot of a probability function](/presentation/dex_prot_probability.png)

In my opinion, it scales fairly well with dexterity and projectile protection. For that reason, I decided not to include in Gothic.ini an option to change parameters of that function.
If you would like to make some changes to the formula, feel free to clone this repository, tweak it and then build the .vdf file (or .dll). Tips on this process can be found [here](https://github.com/Patrix9999/union-plugin-template).

## Requirements

- [Union Primary Universal](https://drive.google.com/file/d/1HujF5KCAKlvqL5Qi8EtiT8GsG5WDpDf2/view)
- [Union 1.0m](https://drive.google.com/file/d/1AkU5qvxIx7zc3kdpGAwlgA-2WiGS7sU5/view) - if you wish to use an older version, you need [zParserExtender](https://worldofplayers.ru/threads/41999/) as well.

## Installation

All you have to do is put **gPenetratingShots.vdf** inside `/Data/Plugins` directory of your Gothic installation. You can download it from the [releases](https://github.com/Kormic1/gPenetratingShots/releases) subpage of this repository.

Enjoy.
