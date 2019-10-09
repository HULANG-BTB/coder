<?php
/**
 * FileName: Category.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 13:37
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */


namespace app\api\controller;


use app\common\controller\Base;
use app\api\model\Category as CategoryModel;
use think\App;

class Category extends Base
{
    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new CategoryModel();
    }

    public function getCategoryList() {

        $result = $this->Model->select();
        $ret = [
            'code' => 1,
            'data' => $result
        ];
        return json($ret);
    }
}
