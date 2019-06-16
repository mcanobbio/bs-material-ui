[@bs.deriving jsConverter]
type margin = [ | [@bs.as "dense"] `Dense];

[@bs.deriving jsConverter]
type variant = [
  | [@bs.as "standard"] `Standard
  | [@bs.as "outlined"] `Outlined
  | [@bs.as "filled"] `Filled
];

module Classes = {
  type classesType =
    | Root(string)
    | Focused(string)
    | Disabled(string)
    | Error(string)
    | Required(string)
    | Asterisk(string)
    | FormControl(string)
    | MarginDense(string)
    | Shrink(string)
    | Animated(string)
    | Filled(string)
    | Outlined(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | Focused(_) => "focused"
    | Disabled(_) => "disabled"
    | Error(_) => "error"
    | Required(_) => "required"
    | Asterisk(_) => "asterisk"
    | FormControl(_) => "formControl"
    | MarginDense(_) => "marginDense"
    | Shrink(_) => "shrink"
    | Animated(_) => "animated"
    | Filled(_) => "filled"
    | Outlined(_) => "outlined";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className)
                         | Focused(className)
                         | Disabled(className)
                         | Error(className)
                         | Required(className)
                         | Asterisk(className)
                         | FormControl(className)
                         | MarginDense(className)
                         | Shrink(className)
                         | Animated(className)
                         | Filled(className)
                         | Outlined(className) =>
                           Js.Dict.set(obj, to_string(classType), className)
                         };
                         obj;
                       },
                     )
                   );
};

[@bs.obj]
external makePropsMui:
  (
    ~children: 'children=?,
    ~className: string=?,
    ~disableAnimation: bool=?,
    ~disabled: bool=?,
    ~error: bool=?,
    ~focused: bool=?,
    ~margin: string=?,
    ~muiFormControl: Js.t({..})=?,
    ~required: bool=?,
    ~shrink: bool=?,
    ~variant: string=?,
    ~filled: bool=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

[@bs.module "@material-ui/core"]
external reactComponent: React.component('a) = "InputLabel";

[@react.component]
let make =
    (
      ~children: option('children)=?,
      ~className: option(string)=?,
      ~disableAnimation: option(bool)=?,
      ~disabled: option(bool)=?,
      ~error: option(bool)=?,
      ~focused: option(bool)=?,
      ~margin: option(margin)=?,
      ~muiFormControl: option(Js.t({..}))=?,
      ~required: option(bool)=?,
      ~shrink: option(bool)=?,
      ~variant: option(variant)=?,
      ~filled: option(bool)=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
    ) =>
  React.createElement(
    reactComponent,
    makePropsMui(
      ~children?,
      ~className?,
      ~disableAnimation?,
      ~disabled?,
      ~error?,
      ~focused?,
      ~margin=?margin->(Belt.Option.map(v => marginToJs(v))),
      ~muiFormControl?,
      ~required?,
      ~shrink?,
      ~variant=?variant->(Belt.Option.map(v => variantToJs(v))),
      ~filled?,
      ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
      ~style?,
      (),
    ),
  );
