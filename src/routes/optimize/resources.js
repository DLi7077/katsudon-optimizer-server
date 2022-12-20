import DEFAULT_OPTIMIZER_STATS from "../../constants/optimize.js";
import { runOptimizer } from "../../utils.js";

export async function optimize(req, res) {
  const characterStats = { ...DEFAULT_OPTIMIZER_STATS, ...req.body };
  const obj = JSON.stringify(characterStats, null, 2);
  const result = await runOptimizer(obj).then((res) => JSON.parse(res));
  res.status(200);
  res.json(result);
}
