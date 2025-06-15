<?php
	class Produto
	{
		public $nome;
		public $custo;
		public $lucropretendido;
		
		public function precovenda() {
			return ($this->custo)+ $this->custo * $this->lucropretendido/100;
		}
		
		public function mostrardados(){
			echo "Produto <br>";
			echo $this->nome. "<br>";
			echo $this->custo. "<br>";
			echo $this->lucropretendido. "<br>";
			echo $this->precovenda(). "<br>";
		}
	}
?>