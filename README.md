# Simulador de Estaleiro de Embarcações de Carga
Este é um simulador desenvolvido como parte de um exercício para criar um sistema de gestão de um estaleiro de embarcações de carga. O simulador permite a gestão de até 10 embarcações, cada uma podendo conter múltiplas pilhas de contentores.

## Funcionalidades Principais
Leitura do Ficheiro de Configuração
O programa pode iniciar a partir de um ficheiro de configuração que descreve a disposição das embarcações e contentores no estaleiro.

## Menu Principal
O simulador apresenta um menu interativo onde o utilizador pode executar várias operações, incluindo mover contentores entre pilhas, mostrar informações sobre embarcações e pontos de atracagem, navegar embarcações para diferentes pontos e muito mais.

## Comandos Disponíveis
move: Move contentores entre pilhas de uma embarcação ou entre diferentes embarcações.
show: Mostra informações sobre as pilhas de contentores de uma embarcação ou de todas as embarcações em determinado ponto.
where: Mostra a localização de uma embarcação no estaleiro.
navigate: Move uma embarcação para outro ponto de atracagem.
load: Adiciona um novo contentor a uma pilha de uma embarcação.
weight: Mostra o peso total de uma embarcação.
save: Guarda a configuração atualizada do estaleiro num ficheiro.
help: Mostra o menu principal.
quit: Termina a execução do simulador.
Implementação
O simulador foi implementado em [linguagem de programação], utilizando uma estrutura de dados para representar as embarcações, pontos de atracagem e contentores. Cada comando do menu principal foi implementado como uma função separada para garantir modularidade e facilidade de manutenção.
