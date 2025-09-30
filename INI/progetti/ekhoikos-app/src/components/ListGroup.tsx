import { useState } from "react";

interface Props {
  items: string[];
  heading: string;
}

function ListGroup({ items, heading }: Props) {
  // Hook (put into a destructured array) - useState(startingValue) sets a "state variable"
  // A "state variable" keeps the data between renders and has a function to update it (and re-renders too)
  const [selectedIndex, setSelectedIndex] = useState(-1);

  // "&&" with the second argument not being a function returns false if the first argument is false, and
  // the second argument if the first argument is true (it's basically a selector)
  return (
    <>
      <h1>{heading}</h1>
      {items.length === 0 && <p>No item found</p>}
      <ul className="list-group">
        {items.map((item, index) => (
          <li
            className={
              selectedIndex === index
                ? "list-group-item active"
                : "list-group-item"
            }
            key={item}
            onClick={() => {
              setSelectedIndex(index);
            }}
          >
            {item}
          </li>
        ))}
      </ul>
    </>
  );
}

export default ListGroup;
