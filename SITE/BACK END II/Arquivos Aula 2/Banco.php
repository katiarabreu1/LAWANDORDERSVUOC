<?php
	include "Conta.php";
	$conta1 = new Conta();
	
	$conta1->saldo = 1000;
    $conta1->agencia= 123;
    $conta1->conta = 4566;
    $conta1->titular = "JOAO DA SILVA";
    $conta1->tipo = "CC";
    $conta1->valorChequeEspecial = 1000;
    $conta1->status = "ABERTA";
	
	$conta1->exibirDetalhes();
	
	//$conta1->depositar(250);
	$conta1->retirar(250);
	
	
	$conta1->exibirDetalhes();
?>