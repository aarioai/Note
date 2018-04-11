<?php
function log($path) {
    $f = fopen($path, 'a');
    while(true) {
        fwrite($f, yield);
    }
}
$l = log('/tmp/log');
$l->send('Hello');   // generator send/current/next ...
$l->send(' ');
$l->send('Aario');
$l->send('!');


function f2() {
    yield 'r';
    yield 'i';
}
function f() {
    yield 'A';
    yield 'a';
    yield f2();
    yield 'o';
}


function parseGenerator(\Generator $g) {
    foreach($g as $i) {
        if($i instanceof \Generator) {
            $i = parseGenerator($i);
        }
        var_dump($i);
    }

    return $i;
}
var_dump(parseGenerator(f()));