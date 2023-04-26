# Yoga

A Defold native extension exposing the [Yoga layout](https://github.com/facebook/yoga) library via a Lua wrapper.

Currently supports macOS, Windows, Linux and HTML5, iOS, and Android.

## Installation

You can use Yoga in your own project by adding this project as a
[Defold library dependency](http://www.defold.com/manuals/libraries/).

Add the latest archive URL from the
[releases page](https://github.com/farism/defold-yoga/releases) to your
dependencies field in `game.project`.

## Usage

Yoga is a high performance C++ library which implements the Flexbox specification. Basic usage consists of four steps:

1. Creating the Yoga nodes and setting their styles
2. Initializing the node tree by attaching children to parents with `set_parent`
3. Calling `calculate_layout` to compute the layout position and size of each node
4. (optional) Updating the Defold Gui nodes using `update_node`

## Caveats

Yoga's layout algorithm assumes you are working in a traditional document coordinate system, with the `(0,0)` being at the top left corner.

However, Defold uses the bottom left corner as `(0,0)`. To account for this the Defold Yoga extension, by default, will apply styles in a way that "inverts" the y-coordinate.

What this essentially means is that setting `FLEX_DIRECTION_COLUMN` will actually set `FLEX_DIRECTION_COLUMN_REVERSE`, and vice-versa.

This also applies to usage of `EDGE_TOP` and `EDGE_BOTTOM`.

To opt-out of this behavior you can disable it by calling `yoga.set_invert_y(false)`.

## Example

The [example in this repo](https://github.com/farism/defold-yoga/tree/main/example) demonstrates a simple three row layout with a fixed size header and footer, and a body that scales to fill the area.

View the [live demo here](https://farism.github.io/defold-yoga)

## Functions

All functions take a gui `node` as their first argument. This is used as the lookup key for the underlying `YGNode`.

`yoga.new_node(node: node): void`

`yoga.update_node(node: node): void`

`yoga.free_node(node: node): void`

`yoga.delete_node(node: node): void`

`yoga.reset_node(node: node): void`

`yoga.set_parent(child: node, parent: node, keep_scene_transform: boolean): void`

`yoga.get_direction(node: node): yoga.DIRECTION`

`yoga.set_direction(node: node, direction: yoga.DIRECTION): void`

`yoga.get_overflow(node: node): yoga.OVERFLOW`

`yoga.set_overflow(node: node, overflow: yoga.OVERFLOW): void`

`yoga.get_display(node: node): yoga.DISPLAY`

`yoga.set_display(node: node, display: yoga.DISPLAY): void`

`yoga.get_position_type(node: node): yoga.POSITION_TYPE`

`yoga.set_position_type(node: node, position_type: yoga.POSITION_TYPE): void`

`yoga.get_position(node: node, edge: yoga.EDGE): number`

`yoga.set_position(node: node, edge: yoga.EDGE, position: any): void`

`yoga.set_position_percent(node: node, edge: yoga.EDGE, position: any): void`

`yoga.get_flex_position(node: node): number`

`yoga.set_flex_position(node: node, flex_position: any): void`

`yoga.get_flex_direction(node: node): number`

`yoga.set_flex_direction(node: node, flex_direction: any): void`

`yoga.get_align_items(node: node): yoga.ALIGN`

`yoga.set_align_items(node: node, align_items: yoga.ALIGN): void`

`yoga.get_align_content(node: node): yoga.ALIGN`

`yoga.set_align_content(node: node, align_content: yoga.ALIGN): void`

`yoga.get_justify_content(node: node): yoga.JUSTIFY`

`yoga.set_justify_content(node: node, justify_content: yoga.JUSTIFY): void`

`yoga.get_grow(node: node): number`

`yoga.set_grow(node: node, grow: number): void`

`yoga.get_shrink(node: node): number`

`yoga.set_shrink(node: node, shrink: number): void`

`yoga.get_basis(node: node): number`

`yoga.set_basis(node: node, basis: number): void`

`yoga.set_basis_percent(node: node, basis: number): void`

`yoga.get_width(node: node): number`

`yoga.set_width(node: node, width: number): void`

`yoga.set_width_percent(node: node, width: number): void`

`yoga.get_min_width(node: node): number`

`yoga.set_min_width(node: node, min_width: number): void`

`yoga.set_min_width_percent(node: node, min_width: number): void`

`yoga.get_max_width(node: node): number`

`yoga.set_max_width(node: node, max_width: number): void`

`yoga.set_max_width_percent(node: node, max_width: number): void`

`yoga.get_height(node: node): number`

`yoga.set_height(node: node, height: number): void`

`yoga.set_height_percent(node: node, height: number): void`

`yoga.get_min_height(node: node): number`

`yoga.set_min_height(node: node, min_height: number): void`

`yoga.set_min_height_percent(node: node, min_height: number): void`

`yoga.get_max_height(node: node): number`

`yoga.set_max_height(node: node, max_height: number): void`

`yoga.set_max_height_percent(node: node, max_height: number): void`

`yoga.get_aspect_ratio(node: node): number`

`yoga.set_aspect_ratio(node: node, aspect_ratio: number): void`

`yoga.get_border(node: node, edge: yoga.EDGE): vmath.vector4`

`yoga.set_border(node: node, edge: yoga.EDGE, border: number): void`

`yoga.get_padding(node: node, edge: yoga.EDGE): vmath.vector4`

`yoga.set_padding(node: node, edge: yoga.EDGE, padding: number): void`

`yoga.set_padding_percent(node: node, edge: yoga.EDGE, padding: number): void`

`yoga.get_margin(node: node, edge: yoga.EDGE): vmath.vector4`

`yoga.set_margin(node: node, edge: yoga.EDGE, margin: number): void`

`yoga.set_margin_percent(node: node, edge: yoga.EDGE, margin: number): void`

`yoga.calculate_layout(node: node): void`

`yoga.get_layout(node: node): { x: number, y: number, width: number, height: number }`

`yoga.get_layout_left(node: node): number`

`yoga.get_layout_top(node: node): number`

`yoga.get_layout_right(node: node): number`

`yoga.get_layout_bottom(node: node): number`

`yoga.get_layout_width(node: node): number`

`yoga.get_layout_height(node: node): number`

`yoga.get_layout_border(node: node): number`

`yoga.get_layout_margin(node: node): number`

`yoga.get_layout_padding(node: node): number`

`yoga.set_capcity(capacity: number): void`

# LICENSE

MIT License