import sys
from dataclasses import dataclass


@dataclass
class Draw:
    red: int
    green: int
    blue: int

    @classmethod
    def from_string(cls, string):
        color_spec_strings = string.split(",")
        kw = {
            "red": 0,
            "green": 0,
            "blue": 0
        }
        for spec in color_spec_strings:
            n_drawn, color = spec.split()
            kw[color.strip().lower()] = int(n_drawn)
        return cls(**kw)

    def asdict(self):
        return {
            "red": self.red,
            "green": self.green,
            "blue": self.blue,
        }


@dataclass
class Game:
    id: int
    draws: list[Draw]

    @classmethod
    def from_string(cls, string):
        game_str, draws_str = string.split(":")
        game_id = int(game_str.split()[-1])

        draws = [Draw.from_string(s.strip()) for s in draws_str.split(";")]
        return cls(id=game_id, draws=draws)

games = [Game.from_string(s) for s in sys.stdin.readlines()]

# part one
# red_cutoff = 12
# green_cutoff = 13
# blue_cutoff = 14
# 
# id_sum = 0
# for game in games:
#     check = all(
#         (draw.red <= red_cutoff and draw.green <= green_cutoff and draw.blue <= blue_cutoff)
#         for draw in game.draws
#     )
#     if check:
#         id_sum += game.id
# print(id_sum)

# part two

power_sum = 0
for game in games:
    min_red = min_green = min_blue = 0
    for draw in game.draws:
        if draw.red > min_red:
            min_red = draw.red
        if draw.green > min_green:
            min_green = draw.green
        if draw.blue > min_blue:
            min_blue = draw.blue
    power_sum += min_red * min_green * min_blue
print(power_sum)
