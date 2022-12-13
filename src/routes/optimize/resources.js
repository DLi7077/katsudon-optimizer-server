import DEFAULT_OPTIMIZER_STATS from "../../constants/optimize.js";

export async function optimize(req, res) {
  const characterStats = { ...DEFAULT_OPTIMIZER_STATS, ...req.body };
  res.status(200);
  res.json(characterStats);
}
