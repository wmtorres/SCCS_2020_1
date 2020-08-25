# SCCS_2020_1
Projeto da Disciplina de Sistemas de Conforto, Conveniência e Segurança - FATEC Santo André

Esses são os arquivos basea para a construção do projeto de um painel de instrumentos automotivo.

```plantuml
@startuml
    skinparam backgroundColor #EEEBDC
    skinparam handwritten true
    actor Customer
    Customer -> "login()" : username & password
    "login()" -> Customer : session token
    activate "login()"
    Customer -> "placeOrder()" : session token, order info
    "placeOrder()" -> Customer : ok
    Customer -> "logout()"
    "logout()" -> Customer : ok
    deactivate "login()"
@enduml
```
