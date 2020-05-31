use std::io;

fn main() -> io::Result<()> {
    let mut input = String::new();

    io::stdin().read_line(&mut input)?;

    println!("Input: {}", &input);

    let value: i32 = input.trim_end().parse::<i32>().expect("Could not convert input to number.");

    println!("Fibonacci Number: {}", fibn(&value)?);
    Ok(())
}

fn fibn(number: &i32) -> Result<i32, io::Error> {
    let mut previous = 1;
    let mut current = 0;
    for _x in 0..*number {
        current = current + previous;
        previous = current;
    }
    Ok(current)
}