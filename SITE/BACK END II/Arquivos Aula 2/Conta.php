<?php

class Conta {
    public $saldo;
    public $agencia;
    public $conta;
    public $titular;
    public $tipo;
    public $valorChequeEspecial;
    public $status;
	
	
	public function depositar ($valor){
		$this->saldo = $this->saldo + $valor;
	}
	
	public function retirar ($valor){
		if ($valor < 200)
			$this->saldo = $this->saldo - $valor;
	}	
	
    public function exibirDetalhes(){
		echo "=======================</br>";
        echo "Titular: " . $this->titular . "</br>";
        //echo "Agência: " . $this->agencia . "</br>";
        //echo "Conta: " . $this->conta . "</br>";
        echo "Saldo: R$" . $this->saldo . "</br>";
        //echo "Tipo: " . $this->tipo . "</br>";
        echo "Cheque Especial: R$" . $this->valorChequeEspecial . "</br>";
        echo "Status: " . $this->status . "</br>";
    }
}
?>