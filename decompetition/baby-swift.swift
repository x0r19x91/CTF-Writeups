func setup() -> Set<String> {
  //
  var ans = Set<String>()
  ans.insert("🌭")
  ans.insert("HOTDOG")
  ans.insert("HOT DOG")
  ans.insert("HOT-DOG")
  ans.insert("SAUSAGE")
  ans.insert("BRATWURST")
  ans.insert("FRANKFURTER")
  ans.insert("POLISH SAUSAGE")
  return ans
}
func query() -> String {
  print("What do you have there?")
  return readLine()!
}

func clean(_ input: String) -> String {
  var fuck = input.uppercased()
  if fuck.starts(with: "A ") {
    fuck.removeFirst(2)
  } else if fuck.starts(with: "THE ") {
    fuck.removeFirst(4)
  }
  return fuck
}

/////
let hotdogs = setup()
let found = clean(query())
if hotdogs.contains(found) {
  print("HOTDOG")
} else {
  print("NOT HOTDOG")
}
