## Katsudon Optimizer Server

### Routes

To create ceiling computation request:\
`POST: api/optimizer/request/create`

<details style="margin-left:1rem;">
<summary><code>Example with Raiden's ceiling:</code></summary>

<details style="margin-left:1rem;">
<summary><code>Request Body:</code></summary>

```js
  {
    "character": { // raiden stats with bonuses
      "stats": {
        "level": 90,
        "element": "Electro",
        "base_attack": 945.31,
        "base_hp": 12907,
        "crit_damage": 0.6,
        "flat_attack": 1105.533408,
        "attack_percent": 1.28,
        "hp_percent": 0,
        "energy_recharge": 2.5713,
        "elemental_mastery": 650,
        "damage_bonus_elemental": 0.8712,
        "damage_bonus_all": 0.27, // bonus talent damage also goes here
        "defense_shred": 0.6
      },
      "talent_scalings": [ // talent scaling
        {
          "talent_stat": "total_attack",
          "talent_percent": 13.473
        }
      ],
      "bonus_stat_gain": [
        { // raiden a4
          "source_stat": "energy_recharge",
          "target_stat": "Electro DMG Bonus%",
          "source_offset": 1.00, // every ER% over 100%
          "percent_gain": 0.4,
          "max_gain": 0 // default 0 means no maximum
        },
        { // r5 englufing lightning
          "source_stat": "energy_recharge",
          "target_stat": "ATK %",
          "source_offset": 1.00, // every ER% over 100%
          "percent_gain": 0.56,
          "max_gain": 1.20 // max possible bonus
        },
        { // 4 piece emblem
          "source_stat": "energy_recharge",
          "target_stat": "Other DMG Bonus%",
          "source_offset": 0,
          "percent_gain": 0.25,
          "max_gain": 0.75
        }
      ]
    },
    "enemy": {
      "level": 90,
      "affected_element": "Dendro", // Electro on dendro for aggravate
      "incoming_damage_element": "Electro",
      "resistance_to_damage_element": -1.2,
      "defense_percent_dropped": 0.3 // Nahida C2
    },
    // help the optimizer go faster by telling it what substats it should use
    "stat_preferences": {
      "substats": [ // at least 5 substats are required
        "Flat Attack",
        "ATK %",
        "Elemental Mastery",
        "Energy Recharge%",
        "Crit Damage"
      ],
      "flower_main_stats": [ // always Flat HP
        "Flat HP"
      ],
      "feather_main_stats": [ // always Flat Attack
        "Flat Attack"
      ],
      "sands_main_stats": [ // at least one valid main stat
        "ATK %",
        "Energy Recharge%"
      ],
      "goblet_main_stats": [ // at least one valid main stat
        "Electro DMG Bonus%",
        "ATK %"
      ],
      "circlet_main_stats": [ // at least one valid main stat
        "ATK %",
        "Crit Damage"
      ]
    }
  }
```

</details>

<details style="margin-left:1rem;">
<summary><code>Response Body:</code></summary>

```js
{
  "_id": "63a6875d3435afe7ede021af", // use this request_id like it's your order number
  "character": {
    "stats": {
      "element": "Electro",
      "base_attack": 945.31,
      "base_hp": 12907,
      "base_def": 0,
      "flat_attack": 1105.533408,
      "attack_percent": 1.28,
      "flat_hp": 0,
      "hp_percent": 0,
      "flat_def": 0,
      "def_percent": 0,
      "elemental_mastery": 650,
      "energy_recharge": 2.5713,
      "crit_rate": 0,
      "crit_damage": 0.6,
      "damage_bonus_elemental": 0.8712,
      "damage_bonus_all": 0.27,
      "melt_bonus": 0,
      "base_damage_bonus": 0,
      "defense_shred": 0.6,
      "quicken_bonus": 0,
      "level": 90
    },
    "talent_scalings": [
      {
        "talent_stat": "total_attack",
        "talent_percent": 13.473
      }
    ],
    "bonus_stat_gain": [
      {
        "source_stat": "energy_recharge",
        "target_stat": "Electro DMG Bonus%",
        "source_offset": 1,
        "percent_gain": 0.4,
        "max_gain": 0
      },
      {
        "source_stat": "energy_recharge",
        "target_stat": "ATK %",
        "source_offset": 1,
        "percent_gain": 0.56,
        "max_gain": 1.2
      },
      {
        "source_stat": "energy_recharge",
        "target_stat": "Other DMG Bonus%",
        "source_offset": 0,
        "percent_gain": 0.25,
        "max_gain": 0.75
      }
    ],
    "stat_preferences": {
      "substats": [
        "Flat Attack",
        "ATK %",
        "Elemental Mastery",
        "Energy Recharge%",
        "Crit Damage"
      ],
      "flower_main_stats": [
        "Flat HP"
      ],
      "feather_main_stats": [
        "Flat Attack"
      ],
      "sands_main_stats": [
        "ATK %",
        "Energy Recharge%"
      ],
      "goblet_main_stats": [
        "Electro DMG Bonus%",
        "ATK %"
      ],
      "circlet_main_stats": [
        "ATK %",
        "Crit Damage"
      ]
    }
  },
  "enemy": {
    "enemy_level": 0,
    "affected_element": "Dendro",
    "resistance_to_damage_element": -1.2,
    "defense_percent_dropped": 0.3,
    "level": 90,
    "incoming_damage_element": "Electro"
  },
  "status": "pending", // current status of the request
  "created_at": "2022-12-24T05:00:13.521Z",
  "__v": 0
}
```

</details>

</details>

- To check on the status of your request: `GET api/optimizer/result?id=result_id`
  - `response.status` is "pending" | "in progress" | "completed"
- if `response.status` == "completed", then there will be a field called "result" that contains the result.
