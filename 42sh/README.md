# 42sh

# Members
* Stanislas Mondesir | smondesir
* Boris Jovanovic | bjovanov
* Cedric Bodenhorst | bcedric
* Viktor Jovanovic | vjovanov
* Sacha Stinglhamber | sstinglh

# Getting started

## Partie obligatoire

## Partie modulaire

1. Les inhibiteurs ” (double quote), ’ (simple quote) et \ (backslash)
2. Gestion complete de l'historique + commande fc 
3. Gestion des alias
4. Gestions des completions dynamiques
5. Built-in test
6. Built in hash + table de hashage

# Stuctures
### Listes chainees

```
token
{
  next,
  previous,
  right,
  left,
  token_name, | ex: "pipe", "brackets", etc
  token_word, | ex: " | " , " {} "    , etc  
  priority
}
```

```
var
{
  struct env,
  struct internal
}
```

```
// environnement herite

env
{
  key,
  value
}
```

```
// environnement interne

internal
{
  key,
  value
}
```

### tableau de structure

```
allowed_token
{
  name,
  word,
  priority
}
```

# Code rules
  
  * Travailler a la norme constamment
    * Respecter le nombre de ligne de fonction
    * Respecter le nombre de caractere par ligne
  * Travailler sans leaks
    * Automatiquement liberer la memoire qui n'est plus utilise
  * Bien commenter son code
    * (utiliser des IDE pour generer des commentaires)
    
# Documentation

Le [Google Doc](https://docs.google.com/spreadsheets/d/1VeSZZHzlY1hvRROrgqOc264Me7e8fUUSqnzcKAhDDDc/edit#gid=0)
