enum ELEMENTS {
  ANEMO = "Anemo",
  CRYO = "Cryo",
  DENDRO = "Dendro",
  ELECTRO = "Electro",
  GEO = "Geo",
  HYDRO = "Hydro",
  PYRO = "Pyro",
  PHYSICAL = "Physical",
}

type Element =
  | ELEMENTS.ANEMO
  | ELEMENTS.CRYO
  | ELEMENTS.DENDRO
  | ELEMENTS.ELECTRO
  | ELEMENTS.HYDRO
  | ELEMENTS.PYRO
  | ELEMENTS.PHYSICAL;

export default Element;
