/** @noSelf */
declare namespace yoga {
  export function new_node(node: node): any
  export function free_node(node: node): any
  export function free_node_recursive(node: node): any
  export function calculate_layout(node: node): any
  export function set_style(node: node, style: Style): any
  export function set_parent(child: node, parent: node, keep_scene_transform: boolean): any
  export function get_direction(node: node): number
  export function set_direction(node: node, direction: any): void
  export function get_overflow(node: node): number
  export function set_overflow(node: node, overflow: any): void
  export function get_display(node: node): number
  export function set_display(node: node, display: any): void
  export function get_position_type(node: node): number
  export function set_position_type(node: node, position_type: any): void
  export function get_position(node: node, edge: any): number
  export function set_position(node: node, edge: any, position: any): void
  export function get_flex_position(node: node): number
  export function set_flex_position(node: node, flex_position: any): void
  export function get_flex_direction(node: node): number
  export function set_flex_direction(node: node, flex_direction: any): void
  export function get_align_items(node: node): number
  export function set_align_items(node: node, align_items: any): void
  export function get_align_content(node: node): number
  export function set_align_content(node: node, align_content: any): void
  export function get_justify_content(node: node): number
  export function set_justify_content(node: node, justify_content: any): void
  export function get_grow(node: node): number
  export function set_grow(node: node, grow: number): void
  export function get_shrink(node: node): number
  export function set_shrink(node: node, shrink: number): void
  export function get_basis(node: node): number
  export function set_basis(node: node, basis: number): void
  export function get_width(node: node): number
  export function set_width(node: node, width: number): void
  export function get_min_width(node: node): number
  export function set_min_width(node: node, min_width: number): void
  export function get_max_width(node: node): number
  export function set_max_width(node: node, max_width: number): void
  export function get_height(node: node): number
  export function set_height(node: node, height: number): void
  export function get_min_height(node: node): number
  export function set_min_height(node: node, min_height: number): void
  export function get_max_height(node: node): number
  export function set_max_height(node: node, max_height: number): void
  export function get_aspect_ratio(node: node): number
  export function set_aspect_ratio(node: node, aspect_ratio: number): void
  export function get_padding(node: node, edge: any): vmath.vector4
  export function set_padding(node: node, edge: any, padding: number): void
  export function get_margin(node: node, edge: any): vmath.vector4
  export function set_margin(node: node, edge: any, margin: number): void
  export function get_layout(node: node): {x:number,y:number,width:number,height:number}
  export function set_layout(node: node, layout: any): void
}