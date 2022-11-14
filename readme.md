# CHESS ♟

(not to be confused with the word [cheese](https://en.wikipedia.org/wiki/Cheese))

This chess is made with c++ 17 and [sfml](https://www.sfml-dev.org) for windows.

(not finished but playable)

<img src="https://user-images.githubusercontent.com/79871802/201465068-6ce77744-7d95-4b19-acba-033f68d471c2.png" alt="example" width="500"/>

## Downloads

Just head to the releases page to download a statically compiled version;

or if you want to build it yourself with `cmake` you need to make sure to install [sfml](https://www.sfml-dev.org) before that.

## Modifications

You can change all the images in the [`pieces`](https://github.com/stifskere/chess/tree/main/cmake-build-debug/pieces) folder, just don't change image names, any image modification must be `60px x 60px`.

If you want to change the table layout, modify the [`table.tbs`](https://github.com/stifskere/chess/blob/main/cmake-build-debug/table.tbs) file (all the values are case-sensitive), if the file is deleted another one will be generated automatically.

#### table names

Table layout consists of 2 parts, the first one named `tb` that means table, and it's value represents the size as an integer.

And the second part is the table layout that is how the pieces are placed in the table, the piece names are the following:

- black pawn: bp
- black tower: bt
- black horse: bh
- black bishop: bb
- black queen: bq
- black king: bk
- white pawn: wp
- white tower: wt
- white horse: wh
- white bishop: wb
- white queen: wq
- white king: wk
- empty: mt

To finish the configuration simply put `end` at the end of the table.

There is another value that's `ck` that means `can kill`, if that value is true you will be able to kill the king in game and the game won't end, otherwise it will.

The `ck` option is quite bug, so by default it's enabled meaning you can kill the king.
#### configuration defaults

the default file for reference looks the following:

```
ck true
tb 8
bt bh bb bq bk bb bh bt
bp bp bp bp bp bp bp bp
mt mt mt mt mt mt mt mt
mt mt mt mt mt mt mt mt
mt mt mt mt mt mt mt mt
mt mt mt mt mt mt mt mt
wp wp wp wp wp wp wp wp
wt wh wb wq wk wb wh wt
end
```

#### default image names

for reference prefix b means black and prefix w means white, if any image is missing game might not run correctly or even start.

- b_bishop.png
- b_horse.png
- b_king.png
- b_queen.png
- b_tower.png
- b_pawn.png
- w_bishop.png
- w_horse.png
- w_king.png
- w_queen.png
- w_tower.png
- w_pawn.png
- chessIcon.png
