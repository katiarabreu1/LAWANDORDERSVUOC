<?php
	include "Produto.php";
	
	$produto1 = new Produto();
	$produto1->nome = "Caneta";
	$produto1->custo = 2.00;
	$produto1->lucropretendido = 60.00;
	
	$produto2 = new Produto();
	$produto2->nome = "Lapis";
	$produto2->custo = 1.30;
	$produto2->lucropretendido = 65.00;

	$produto1->mostrardados();
	$produto2->mostrardados();

?>