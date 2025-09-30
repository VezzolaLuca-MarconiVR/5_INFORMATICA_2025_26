import { useState, type JSX } from "react";

function ListGroup() {
  let items = ["NY", "SF"];
  // Hook (put into a destructured array)
  const [selectedIndex, setSelectedIndex] = useState(-1);

  const getMessage = (): JSX.Element | false => {
    return items.length === 0 && <p>No item found</p>;
  };

  return (
    <>
      <h1>List</h1>
      {getMessage()}
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
