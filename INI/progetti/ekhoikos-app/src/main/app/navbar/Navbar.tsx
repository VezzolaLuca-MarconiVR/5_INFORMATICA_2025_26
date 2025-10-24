import ToggleThemeButton from "./ToggleThemeButton";

function Navbar() {
  return (
    <>
      <nav>
        <ul>
          <li>
            <a href="index.html" className="active">
              Home
            </a>
          </li>
          <li>
            <a href="shop.html">Shop</a>
          </li>
          <li>
            <a href="sales.html">Sales</a>
          </li>
          <li>
            <a href="chat.html">Chat</a>
          </li>
          <li style={{ float: "right" }}>
            <a href="userInfo.html">User Info</a>
          </li>
          <li style={{ float: "right" }}>
            <ToggleThemeButton />
          </li>
        </ul>
      </nav>
    </>
  );
}

export default Navbar;
